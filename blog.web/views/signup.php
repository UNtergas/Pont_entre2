<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?= $data['page_title']; ?></title>
</head>

<body>
    <h1>SIGNUP PAGE</h1>
    <?php check_message() ?>
    <br>
    <a href="<?= ROOT ?>home">BACK TO HOME</a>
    <br>
    <a href="<?= ROOT ?>login"> Already have an account? Login now</a>
    <br>
    <h3>=========</h3>
    <div class="signup_page">
        <form class="signup" method="post">
            <input type="text" name="username" placeholder="name" />
            <br>
            <input type="password" name="password" placeholder="password">
            <br>
            <button>LOGIN</button>
        </form>
    </div>
</body>

</html>