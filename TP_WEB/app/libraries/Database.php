<?php
class Database
{
    // Informations de la base de données
    private $host = "localhost";
    private $db_name = "hospital";
    private $username = "admin_user";
    private $password = "Keanlk192002";

    // Propriété qui contiendra l'instance de la connexion
    protected $db;

    private $query;

    public function __construct() {
        // On supprime la connexion précédente
        $this->db = null;

        // On essaie de se connecter à la base
        try {
            $this->db = new PDO(
                "mysql:host=" . $this->host . ";dbname=" . $this->db_name, $this->username, $this->password
            );
            $this->db->exec("set names utf8");
        } catch (PDOException $exception) {
            echo "Erreur de connexion : " . $exception->getMessage();
        }
    }

    public function query($sql) {
        $this->query = $this->db->prepare($sql);
    }

    public function execute() {
        if($this->query != null) {
            return $this->query->execute();
        }
    }

    public function resultSet()
    {
        $this->execute();
        return $this->query->fetchAll();
    }

    public function single() {
        $this->execute();
        return $this->query->fetch();
    }

    public function rowCount() {
        return sizeof($this->resultSet());
    }

    public function lastInsertId() {
        return $this->db->lastInsertId();
    }
}

// // Testing
// $database = new Database();
// $database->query("SELECT * FROM doctor WHERE email='An@gmail.com'");
// // $model->table = "doctor";
// var_dump($database->resultSet());



