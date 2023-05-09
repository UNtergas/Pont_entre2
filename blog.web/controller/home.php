<?php

class Home extends Controller
{

    function index()
    {
        $db = new Model();
        // $db->db_connect();
        $data['query'] = $db->read("select * from test_table");
        $data['page_title'] = 'Home Page';
        $this->views('home', $data);
    }
}
