<?php

use Fusion\Cores\Engine;
use Fusion\Cores\Autoload;

session_start();

Engine::Framework(FS_DEFAULT);

Autoload::Config(FS_DEFAULT);
Autoload::Register();

Engine::Run();