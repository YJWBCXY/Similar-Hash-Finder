#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <vector>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/optional.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

mongocxx::instance instance{}; // This should be done only once.
mongocxx::uri uri("mongodb://shf-database:27017");
mongocxx::client client(uri);

class database {
    private:
    mongocxx::database db;
    int64_t TASK_LIMIT = 100;

    public:
    database() {
        db = client["shf_db"];
    }

    int insert_blank(int64_t amount = 10000) {
        mongocxx::collection collection = db["hash"];
        mongocxx::options::find opts;
        opts.sort(make_document(kvp("index", -1)));
        std::optional<bsoncxx::document::value> last_result =
            collection.find_one({}, opts);
        int64_t index;

        if (!last_result) {
            index = 0;
        } else {
            index = last_result.value().view()["index"].get_int64();
        }

        std::vector<bsoncxx::document::value> insert;
        for (int i = 0; i < amount; i++) {
            insert.push_back(
                make_document(kvp("index", index), kvp("state", 0)));
            index++;
        }

        collection.insert_many(insert);

        return 0;
    }

    std::string get_task() {
        mongocxx::collection collection = db["hash"];

        while (true) {
            int64_t count = collection.count_documents(
                make_document(kvp("state", 0)).view());
            if (count < TASK_LIMIT) {
                insert_blank();
            } else {
                break;
            }
        }

        mongocxx::options::find opts;
        opts.sort(make_document(kvp("index", 1)));
        opts.limit(TASK_LIMIT);
        mongocxx::cursor cursor =
            collection.find(make_document(kvp("state", 0)), opts);
        bsoncxx::builder::basic::array task_list;

        mongocxx::bulk_write bulk = collection.create_bulk_write();
        int64_t time_now =
            std::chrono::duration_cast<std::chrono::hours>(
                std::chrono::system_clock::now().time_since_epoch())
                .count();
        for (bsoncxx::document::view doc : cursor) {
            auto index = doc["index"];

            if (index && index.type() == bsoncxx::type::k_int64) {
                int64_t tmp = index.get_int64();
                task_list.append(tmp);

                bulk.append(mongocxx::model::update_one(
                    make_document(kvp("index", tmp)).view(),
                    make_document(kvp("$set", make_document(kvp("state", 1))))
                        .view()));
                bulk.append(mongocxx::model::update_one(
                    make_document(kvp("index", tmp)).view(),
                    make_document(
                        kvp("$set", make_document(kvp("time", time_now))))
                        .view()));
            }
        }
        bulk.execute();

        bsoncxx::builder::basic::document doc_builder;
        doc_builder.append(kvp("data", task_list));

        return bsoncxx::to_json(doc_builder.view());
    }

    void insert_result(std::string input) {
        bsoncxx::document::value json = bsoncxx::from_json(input);
        mongocxx::collection collection = db["contributors"];
        bsoncxx::document::element user = json["user"];

        int contributor_id;
        if (user) {
            bsoncxx::types::b_string contributor_name = user.get_string();
            std::optional<bsoncxx::document::value> contributor =
                collection.find_one(
                    make_document(kvp("name", contributor_name)));
            if (contributor) {
                contributor_id = contributor.value().view()["id"].get_int32();
            } else {
                mongocxx::options::find opts;
                opts.sort(make_document(kvp("id", -1)));
                std::optional<bsoncxx::document::value> contributor =
                    collection.find_one({}, opts);
                if (contributor) {
                    contributor_id =
                        contributor.value().view()["id"].get_int32();
                    contributor_id++;
                } else {
                    contributor_id = 0;
                }
                collection.insert_one(
                    make_document(kvp("name", contributor_name),
                                  kvp("id", contributor_id)));
            }
        }

        collection = db["hash"];
        bsoncxx::document::view data = json["data"].get_document().view();
        mongocxx::bulk_write bulk = collection.create_bulk_write();
        for (bsoncxx::document::element item : data) {
            int64_t index = std::stoll(std::string(item.key()));
            bsoncxx::types::b_string hash = item.get_string();

            bulk.append(mongocxx::model::update_one(
                make_document(kvp("index", index)).view(),
                make_document(kvp("$set", make_document(kvp("hash", hash))))
                    .view()));
            bulk.append(mongocxx::model::update_one(
                make_document(kvp("index", index)).view(),
                make_document(
                    kvp("$set",
                        make_document(kvp("contributor_id", contributor_id))))
                    .view()));
            bulk.append(mongocxx::model::update_one(
                make_document(kvp("index", index)).view(),
                make_document(kvp("$set", make_document(kvp("state", 2))))
                    .view()));
            bulk.append(mongocxx::model::update_one(
                make_document(kvp("index", index)).view(),
                make_document(kvp("$unset", make_document(kvp("time", 1))))
                    .view()));
        }
        bulk.execute();
    }
};