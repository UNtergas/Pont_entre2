<?php

class Login extends Controller
{

    function index()
    {
        if (isset($_POST['username']) && isset($_POST['password'])) {
            $user = $this->loadModel("user");
            $user->login($_POST);
        }

        $data['page_title'] = 'LOGIN';
        $this->views('login', $data);
    }
}