#pragma once

#include <phpcpp.h>

#include <components/gate/route/context.hpp>
#include <http/request/request.hpp>
#include <views/constra/constra.hpp>


#include <iostream>

class DefaultContainer {
    public: Php::Object object_class(std::string method_name) {
        std::map<std::string, Php::Object> dependencies_list;

        dependencies_list["Fusion\\Components\\Gate\\Route\\Context"] = def_route_context();
        dependencies_list["Fusion\\Http\\Request"] = def_request();
        dependencies_list["Fusion\\Views\\Constra"] = def_constra();
    
        return dependencies_list[method_name];
    }

    /**
     * @note List all of default dependencies for DI Fusion.
     * 
     */

    public: Php::Object def_route_context() {
        RouteContext *route_context = new RouteContext;
        return Php::Object("Fusion\\Components\\Gate\\Route\\Context", route_context);
    }

    public: Php::Object def_request() {
        Request *request = new Request;
        return Php::Object("Fusion\\Http\\Request", request);
    }
    
    public: Php::Object def_constra() {
        Constra *constra = new Constra;
        return Php::Object("Fusion\\Views\\Constra", constra);
    }

};