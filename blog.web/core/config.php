<?php

define("WEBSITE_NAME", "My_blog");

define('DB_TYPE', 'mysql');
define('DB_NAME', 'blog_web');
define('DB_USER', 'root');
define('DB_PASS', 'tuanvipe1');
define('DB_HOST', 'localhost');

define('PROTOCAL', 'http');

/**
 * root and path
 */
// $path = str_replace("\\", "/", PROTOCAL . "://" . $_SERVER['SERVER_NAME'] . __DIR__ . "/");
// print_r($path);
// $path = str_replace($_SERVER['DOCUMENT_ROOT'], "", $path);
// echo '<br>';
// print_r($path);
// define('ROOT', str_replace("core", "public", $path));
$path = str_replace('index.php', '', $_SERVER['SCRIPT_FILENAME']);
define('ROOT', str_replace('/var/www/blog.web/public', '.', $path));
define('DEBUG', true);

if (DEBUG) {
    ini_set("display_error", 1);
} else {
    ini_set("display_error", 0);
}
