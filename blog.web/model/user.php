<?php

class User
{
    function login($post)
    {
        $DB = new Model();
        $_SESSION['error'] = '';
        if (isset($post['username']) && isset($post['password'])) {
            $args['username'] = $post['username'];
            $args['password'] = $post['password'];
            $query = "SELECT * FROM users WHERE username = :username AND password = :password limit 1";
            $data = $DB->read($query, $args);
            if (is_array($data)) {
                $_SESSION['userid'] = $data[0]->userid;
                $_SESSION['username'] = $data[0]->username;
                header("Location:" . ROOT . "lobby");
                die;
            } else {
                $_SESSION['error'] = 'wrong username or password';
            }
        } else {
            $_SESSION['error'] = 'invalid username or password';
        }
    }
    function signup($post)
    {
        $DB = new Model();
        $_SESSION['error'] = '';
        if (isset($post['username']) && isset($post['password'])) {
            $args['username'] = $post['username'];
            $args['password'] = $post['password'];
            $query = "INSERT INTO users (username,password) values (:username,:password)";
            $data = $DB->write($query, $args);
            if ($data) {
                header("Location:" . ROOT . "login");
                die;
            }
        } else {
            $_SESSION['error'] = 'invalid username or password';
        }
    }
    function check_login()
    {
        if (isset($_SESSION['userid'])) {
            $args['userid'] = $_SESSION['userid'];
            $query = "SELECT * FROM users WHERE userid = :userid limit 1";
            $DB = new Model();
            $data = $DB->read($query, $args);
            if (is_array($data)) {
                $_SESSION['userid'] = $data[0]->userid;
                $_SESSION['username'] = $data[0]->username;
                return true;
            }
            return false;
        }
    }
}
