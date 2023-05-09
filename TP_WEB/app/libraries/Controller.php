<?php
// define('ROOT', '/home/kean/work/semester_6/web_engineering/TP_web_auth_ver3/');
abstract class Controller{

    public function loadModel(string $model){
        require_once(ROOT . 'app/models/' . $model . '.php');
        // $this->$model = new $model();
        return new $model();
    }
    
    public function render($vue, array $data =[]){
        extract($data);
        // ob_start();
        require_once(ROOT . 'app/views/' . strtolower(get_class($this)) . '/' . $vue . '.php');
        // $content = ob_get_clean();
    }
}
?>