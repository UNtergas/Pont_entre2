<?php
abstract class Controller{
    public function loadModel(string $model){
        require_once(ROOT . 'models/' . $model . ' .php');
        $this->$model = new $model();
    }
    public function render($vue, array $data =[]){
        //var_dump($data)
        echo "<h1> ***********</h1>";
        //var_dump($articles);
        require_once(ROOT . 'views/' . strtolower(get_class($this)) . '/' .$vue . '.php' ); 

    }
}
