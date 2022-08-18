/**
 * @file include.h
 * @author Sultan Ilham (me@onecthree.id)
 * @brief Include header dependencis
 * @version 0.1
 * @date 2022-06-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <phpcpp.h>

#include <cores/engine/engine.hpp>
#include <cores/autoload/autoload.hpp>   

#include <components/gate/route/route.hpp>
#include <components/gate/route/context.hpp>

#include <controllers/controller/controller.hpp>
#include <http/request/input-capture.hpp>
#include <components/gate/route/unit.hpp>

#include <components/gate/route/method/get.hpp>
#include <components/gate/route/method/post.hpp>
#include <components/gate/route/method/head.hpp>
#include <components/gate/route/method/put.hpp>
#include <components/gate/route/method/patch.hpp>
#include <components/gate/route/method/options.hpp>
#include <components/gate/route/method/redirect.hpp>
#include <components/gate/route/method/any.hpp>
#include <components/gate/route/method/method.hpp>

#include <views/constra/constra.hpp>
#include <cores/container/container.hpp>