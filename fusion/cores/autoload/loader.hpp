#pragma once
#include <phpcpp.h>

#include <database/core.hpp>

#include <string>
#include <functional>
#include <dirent.h>

class loader : public Php::Base {
    private: void static list_files(const std::string &path, std::function<void(const std::string &)> cb) {
        if (auto dir = opendir(path.c_str())) {
            while (auto f = readdir(dir)) {
                if (!f->d_name || f->d_name[0] == '.')
                    continue;
                
                if (f->d_type == DT_DIR) 
                    list_files(path + f->d_name + "/", cb);

                if (f->d_type == DT_REG)
                    cb(path + f->d_name);
            }
            closedir(dir);
        }
    }

    private: void static require_src(Php::Value p_directory, bool only_once) {
        std::string directory = p_directory;
        list_files(directory, [&](const std::string &path) {
            if(only_once) {
                Php::require_once(path);
            } else {
                Php::require(path);
            }
        });
    }

    public: void static _default() {
        // MVC client directory
        Php::Value app_config;
        
        app_config["FS_MVC_Client_Dir"]["Controllers"] = "../app/Controllers/";
        app_config["FS_MVC_Client_Dir"]["Models"]      = "../app/Models/";
        // app_config["FS_MVC_Client_Dir"]["Views"]       = "../app/Views/";

        // Routes client directory

        app_config["FS_Routes_Client_Dir"] = "../routes/";

        Database::set::array({"FUSION_STORE", "FS_AUTOLOAD_CONFIG"}, app_config);
        
    }

    public: void static boot() {
        // Register the config as startup used for require_src
        Php::Value app_config = Database::get::array({"FUSION_STORE", "FS_AUTOLOAD_CONFIG"});

        require_src(app_config["FS_MVC_Client_Dir"]["Controllers"], true);   
        require_src(app_config["FS_MVC_Client_Dir"]["Models"], true);
        require_src(app_config["FS_MVC_Client_Dir"]["Views"], true);
        
    }

    public: void static route() {
        Php::Value app_config = Database::get::array({"FUSION_STORE", "FS_AUTOLOAD_CONFIG"});
        require_src(app_config["FS_Routes_Client_Dir"], false);
    }

};