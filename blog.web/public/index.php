<?php
require '../init.php';

if (session_id() == '') {
    session_start();
}
$app = new App();
