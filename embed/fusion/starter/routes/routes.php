<?php

use Fusion\Components\Gate\Route;

Route::any("/", [IndexController::class, "return"]);