<?php

class Signup extends Controller
{

    function index()
    {
        if (isset($_POST['username']) && isset($_POST['password'])) {
            $user = $this->loadModel("user");
            $user->signup($_POST);
        }
        $data['page_title'] = 'SIGN UP';
        $this->views('signup', $data);
    }
}
