<?php
// require_once("/home/kean/work/semester_6/web_engineering/TP_web_auth_ver3/app/libraries/Controller.php");

class Doctors extends Controller
{
    public function __construct()
    {
        $this->UserModel = $this->loadModel("Doctor");
    }

    public function login()
    {
        // echo $_SERVER['REQUEST_METHOD'];
        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            if (isset($_POST['email']) && isset($_POST['password'])) {
                $result = $this->UserModel->login($_POST['email'], $_POST['password']);
                if ($result) {
                    header('Location: /');
                    die;
                } else {
                    echo 'wrong email or password';
                }
            }
        } else if ($_SERVER['REQUEST_METHOD'] === 'GET') {
            $this->render("login", []);
        }
    }
    public function register()
    {
        if ($_SERVER['REQUEST_METHOD'] === 'POST') {
            if (isset($_POST['email']) && isset($_POST['password'])) {
                $result = $this->UserModel->create($_POST['email'], $_POST['password']);
                if ($result) {
                    header('Location: /');
                    die;
                }
            }
        } else if ($_SERVER['REQUEST_METHOD'] === 'GET') {
            $this->render("login", []);
        }
    }
}
