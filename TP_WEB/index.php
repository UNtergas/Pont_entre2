<?php

// On génère une constante contenant le chemin vers la racine publique du projet
define('ROOT', str_replace('index.php', '', $_SERVER['SCRIPT_FILENAME']));
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

// import the Controller and Database at root to let the child controller and child model can extend
require_once(ROOT . 'app/libraries/Controller.php');
require_once(ROOT . 'app/libraries/Database.php');

$url = $_SERVER['REQUEST_URI'];
$route = explode("?", $url);
echo "route: " . $route[0];
echo "<br>";

// Router
switch ($route[0]) {
    case '/':
        if ($_SERVER['REQUEST_METHOD'] === 'GET') {
            require_once(ROOT . 'public/index.php');
        }
        break;

    case '/doctors/login':

        require_once(ROOT . 'app/controllers/Doctors.php');
        $doctorController = new Doctors();
        $doctorController->login();

        break;
    case '/doctors/register':
        require_once(ROOT . 'app/controllers/Doctors.php');
        $doctorController = new Doctors();
        $doctorController->register();

        break;
}
