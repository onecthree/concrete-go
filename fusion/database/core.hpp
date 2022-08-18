#pragma once

#include <phpcpp.h>

#include <iostream>
#include <vector>

namespace Database {
    class set : public Php::Base {
        public: void static boolean(std::vector<std::string> array_index, bool value) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }

            std::string s_value = value ? "1" : "0";

            Php::eval("$_SESSION" +merge_array_index+ " = " +s_value+ ";");
        }

        public: void static string(std::vector<std::string> array_index, std::string value) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }

            Php::eval("$_SESSION" +merge_array_index+ " = '" +value+ "';");
        }

        public: void static number(std::vector<std::string> array_index, double value) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }   

            Php::eval("$_SESSION" +merge_array_index+ " = " +std::to_string(value)+ ";");
        }

        public: void static array(std::vector<std::string> array_index, Php::Value value) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }   
            
            std::string string_array_value = Php::call("json_encode", value); 

            Php::eval("$_SESSION" +merge_array_index+ " = json_decode('" +string_array_value+ "', true);");
        }

        public: void static push_array_string(std::vector<std::string> array_index, std::string value) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }   
            
            Php::eval("$_SESSION" +merge_array_index+ "[] = '" +value+ "';");
        }

        public: void static push_array_int(std::vector<std::string> array_index, std::string value) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }   
            
            Php::eval("$_SESSION" +merge_array_index+ "[] = " +value+ ";");
        }

        public: void static push_array_array(std::vector<std::string> array_index, Php::Value value) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }   
            
            std::string v_value = Php::call("json_encode", value);

            Php::eval("$_SESSION" +merge_array_index+ "[] = json_decode('" +v_value+ "', true);");
        }

        public: void static empty_array(std::vector<std::string> array_index) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }   
            
            Php::eval("$_SESSION" +merge_array_index+ " = array();");
        }
    };

    class get : public Php::Base {
        public: bool static boolean(std::vector<std::string> array_index) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }

            bool b_ret_from_eval = Php::eval("return @$_SESSION" +merge_array_index+ ";").boolValue();
            // bool b_ret_from_eval = ret_from_eval;
            
            return b_ret_from_eval;
        }

        public: std::string static string(std::vector<std::string> array_index) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }

            Php::Value ret_from_eval = Php::eval("return @$_SESSION" +merge_array_index+ ";").stringValue();
            std::string s_ret_from_eval = ret_from_eval;
            
            return s_ret_from_eval;
        }

        public: double static number(std::vector<std::string> array_index) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }

            Php::Value ret_from_eval = Php::eval("return $_SESSION" +merge_array_index+ ";").floatValue();
            
            return ret_from_eval;
        }

        public: Php::Value static array(std::vector<std::string> array_index) {
            std::string merge_array_index = "";
            
            for(auto &index: array_index) {
                merge_array_index += "['" +index+ "']";
            }

            Php::Value ret_from_eval = Php::eval("return json_encode($_SESSION" +merge_array_index+ ");").stringValue();
            Php::Value conv_ret_from_eval = Php::call("json_decode", ret_from_eval, true);
            
            return conv_ret_from_eval;
        }
    };

    class isset : public Php::Base {
        public: bool static string(std::string value) {
            if(value == "") {
                return false;
            } else {
                return true;
            }
        }
    };

    void unset(std::vector<std::string> array_index) {
        std::string merge_array_index = "";
        
        for(auto &index: array_index) {
            merge_array_index += "['" +index+ "']";
        }

        Php::eval("unset($_SESSION" +merge_array_index+ ");");
    };

    std::string session_id() {
        return Php::call("session_id");
    }

    void reset() {
        Php::call("session_destroy");
    }
}