<?php

class Lobby extends Controller
{

    function index()
    {
        $data['page_title'] = 'LOBBY';
        $this->views('lobby', $data);
    }
}
