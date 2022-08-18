#include <includes.h>

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        static Php::Extension extension("fusion", "1.0");

        Php::Namespace fusion("Fusion");

        Php::Class<Engine>          engine("Cores\\Engine");
        Php::Class<Autoload>        autoload("Cores\\Autoload");
        Php::Class<Route>           route("Components\\Gate\\Route");
        Php::Class<RouteContext>    route_context("Components\\Gate\\Route\\Context");
        Php::Class<Controller>      controller("Controllers\\Controller");
        
        Php::Class<Request>         request("Http\\Request");
        Php::Class<RouteGet>        route_get("Components\\Gate\\Route\\Method\\Get");
        Php::Class<RoutePost>       route_post("Components\\Gate\\Route\\Method\\Post");
        Php::Class<RouteHead>       route_head("Components\\Gate\\Route\\Method\\Head");
        Php::Class<RoutePut>        route_put("Components\\Gate\\Route\\Method\\Put");
        Php::Class<RoutePatch>      route_patch("Components\\Gate\\Route\\Method\\Patch");
        Php::Class<RouteOptions>    route_options("Components\\Gate\\Route\\Method\\Options");
        Php::Class<RouteRedirect>   route_redirect("Components\\Gate\\Route\\Method\\Redirect");
        Php::Class<RouteAny>        route_any("Components\\Gate\\Route\\Method\\Any");
        Php::Class<RouteMethod>     route_method("Components\\Gate\\Route\\Method\\Method");

        Php::Class<Constra>         constra("Views\\Constra");
        
        constra.method<&Constra::__construct>("__construct", {});
        constra.method<&Constra::__destruct>("__destruct", {});

        Php::Namespace unit("Components\\Gate\\Unit");
        Php::Class<unit::foo> foo("foo");
        Php::Class<unit::bar> bar("bar");

        // routeget.method<&RouteGet::test>("test", {});

        // constra.method<&Constra::test>("test", {});

        foo.method<&unit::foo::foo_u>("foo_u", {});
        bar.method<&unit::bar::bar_u>("bar_u", {});

        unit.add(std::move(foo));
        unit.add(std::move(bar));

        engine.method<&Engine::Framework>("Framework", {});
        engine.method<&Engine::Run>("Run", {});

        autoload.method<&Autoload::Config>("Config", {});
        autoload.method<&Autoload::Register>("Register", {});

        route.method<&Route::get>("Get", {});
        route.method<&Route::post>("Post", {});
        route.method<&Route::head>("Head", {});
        route.method<&Route::put>("Put", {});
        route.method<&Route::patch>("Patch", {});
        route.method<&Route::options>("Options", {});
        route.method<&Route::redirect>("Redirect", {});
        route.method<&Route::any>("Any", {});
        route.method<&Route::method>("Method", {});

        route_context.method<&RouteContext::code_501>("code_501", {});

        controller.method<&Controller::Class>("Class", {});
        
        request.method<&Request::__construct>("__construct", {});
        request.method<&Request::uri>("uri", {});
        request.method<&Request::get>("get", {});

        fusion.add(std::move(engine));
        fusion.add(std::move(autoload));
        fusion.add(std::move(route));
        fusion.add(std::move(route_context));

        fusion.add(std::move(route_get));
        fusion.add(std::move(route_post));
        fusion.add(std::move(route_head));
        fusion.add(std::move(route_put));
        fusion.add(std::move(route_patch));
        fusion.add(std::move(route_options));
        fusion.add(std::move(route_redirect));
        fusion.add(std::move(route_any));
        fusion.add(std::move(route_method));

        fusion.add(std::move(controller));
        fusion.add(std::move(request));
        fusion.add(std::move(unit));
        fusion.add(std::move(constra));

        extension.add(Php::Constant("FS_DEFAULT", "FS_DEFAULT"));
        extension.add(Php::Constant("FS_COMPACT", "FS_COMPACT"));

        // wrapped namespace, add to extension
        extension.add(std::move(fusion));

        return extension;
    }
}
