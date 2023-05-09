<?php
class Controller
{
    protected function views($view, $data = [])
    {
        if (file_exists("../views/" . $view . ".php")) {
            include "../views/" . $view . ".php";
        } else {
            include "../views/404.php";
        }
    }

    protected function loadModel($model)
    {
        if (file_exists("../model/" . $model . ".php")) {
            include "../model/" . $model . ".php";
            return $model = new $model();
        }
        return false;
    }
}
