#pragma once

#include <optional>
#include <string>
#include <vector>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/stdx/optional.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;

mongocxx::instance instance{}; // This should be done only once.
mongocxx::uri uri("mongodb://shf-database:27017");
mongocxx::client client(uri);

class database {
    private:
        mongocxx::database db;
    public:
        database(){
            db = client["shf_db"];
        }

        int insert_blank(){
            mongocxx::collection collection = db["hash"];
            mongocxx::options::find opts;
            opts.sort(make_document(kvp("index", -1)));
            std::optional<bsoncxx::document::value> last_result = collection.find_one({}, opts);
            int64_t index;
    
            if (!last_result){
                index=0;
            }else{
                index = last_result.value().view()["index"].get_int64();
            }
    
            std::vector<bsoncxx::document::value> insert;
            for (int i = 0; i < 10000; i++){
            insert.push_back(make_document(
                kvp("index", index),
                kvp("state", 0)
            ));
            index++;
            }

            collection.insert_many(insert);

            return 0;
        }
};