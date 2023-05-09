<?php

class Model
{

    // private $host = "localhost";
    // private $dbname = "blog";
    // private $username = "root";
    // private $password = "orange";
    private $host = "localhost";
    private $dbname = "TD_article";
    private $username = "root";
    private $password = "tuanvipe1";

    protected $_connexion;
    public $table;
    public $id;

    public function getConnection()
    {
        $this->_connexion = null;
        try {

            $this->_connexion = new PDO(

                'mysql:host=' . $this->host . ';dbname=' . $this->dbname,
                $this->username,
                $this->password
            );
        } catch (PDOException $exception) {
            echo "Err : " . $exception->getMessage();
        }
    }

    public function getAll()
    {
        $sql = "SELECT *FROM " . $this->table;

        $query = $this->_connexion->prepare($sql);
        $query->execute();
        return $query->fetchAll();
    }

    public function getOne()
    {

        $sql = "SELECT * FROM " . $this->table . "where id=" . $this->id;
        $query = $this->_connexion->prepare($sql);

        $query->execute();

        return $query->fetch();
    }
}

//Test1: Abstract Model 
$m = new Model();
$m->getConnection();
$m->table = "posts";
// var_dump($m->getAll());
$return  = $m->getAll();
foreach ($return as $row) {
    echo ">>" . implode(",", $row) . "\n";
}
