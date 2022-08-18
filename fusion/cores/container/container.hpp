#pragma once

#include <phpcpp.h>

#include <http/request/request.hpp>
#include <cores/container/default.hpp>

#include <iostream>
#include <vector>

namespace Container {

    Php::Object default_list(std::string type_name) {

        /**
         * @note Fusion import the default class all lib injection
         *       which is stored in ./default.h
         * 
         *      ** The default class all from fusion enviroment, which auto included when user type-hint in parameter.
         */
        DefaultContainer default_container;
        return default_container.object_class(type_name);
    }

    class Loader : public Php::Base {

        /**
         * @brief A method used for return object a selected dependencies for each type
         * 
         * @param type_name (std::string) used for selecting type class name based string name class
         * 
         * @return (Pho::Object) A Object based for PHP Context, returned current context dependencies. 
         * 
         */
        // private: Php::Object static default_list(std::string type_name) {

        //     /**
        //      * @note Fusion import the default class all lib injection
        //      *       which is stored in ./default.h
        //      * 
        //      *      ** The default class all from fusion enviroment, which auto included when user type-hint in parameter.
        //      */
        //     DefaultContainer default_container;
        //     return default_container.object_class(type_name);
        // }

        /**
         * @brief the "Method" method used for Reflection each class-method to get parameter type & interface as list.
         * 
         * @param cclass        (std::string) A param for class name target
         * @param mmethod       (std::stirng) A param for method name target
         * 
         * @return              (std::vector<Php::Object>) return a vector data with (Php::Object) type. each element contains a object method for injection requirements
         * 
         */
        public: std::vector<Php::Value> static Method(std::string class_name, std::string method_name) {
            // Php::Value dependencies = Php::eval("$ps = (new ReflectionMethod('" +class_name+ "', '" +method_name+ "'))->getParameters(); $dp = []; foreach($ps as $p) { $dp[(string) $p->getName()] = (string) $p->getType();}return $dp;").mapValue();
            Php::Value reflect_function = Php::Object("ReflectionMethod", class_name, method_name);
            Php::Value get_param = reflect_function.call("GetParameters").mapValue();

            std::vector<Php::Value> depen_group;
            for(auto &p : get_param) {
                Php::Value get_type = (p.second).call("getType");
                Php::out << (std::string)get_type << std::flush;
                depen_group.push_back(default_list( (std::string)get_type ));
            }
            // for(auto &param : dependencies) {
            //     depen_group.push_back(default_list(param.second));
            // }

            return depen_group;
        }

        /**
         * @brief the "Function" method used for Reflection each function to get parameter type & interface as list.
         * 
         * 
         * @return              (std::vector<Php::Object>) return a vector data with (Php::Object) type. each element contains a object method for injection requirements
         * 
         */
        public: std::vector<Php::Value> static Function(Php::Value function_name) {
            // Php::Value dependencies = Php::eval("$ps = (new ReflectionFunction('" +function_name+ "'))->getParameters(); $dp = []; foreach($ps as $p) { $dp[(string) $p->getName()] = (string) $p->getType();}return $dp;").mapValue();

            Php::Value reflect_function = Php::Object("ReflectionFunction", function_name);
            Php::Value get_param = reflect_function.call("GetParameters").mapValue();

            std::vector<Php::Value> depen_group;
            for(auto &p : get_param) {
                Php::Value get_type = (p.second).call("getType");
                depen_group.push_back(default_list( (std::string)get_type ));
            }

            // std::vector<Php::Value> depen_group;
            // for(auto &param : dependencies) {
            //     depen_group.push_back(default_list(param.second));
            // }

            return depen_group;
        }
    };

}