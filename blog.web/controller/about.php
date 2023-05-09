<?php

class About extends Controller
{

    function index()
    {
        $data['page_title'] = 'About Page';
        $this->views('about', $data);
    }
}
