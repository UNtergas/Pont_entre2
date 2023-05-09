<!DOCTYPE html>
<html>
<head>
	<title>Login Page</title>
</head>
<body>
	<h2>Login Page</h2>
	<form action="/doctors/login" method="POST">
		<label for="email">email:</label>
		<input type="text" id="email" name="email" required><br><br>
		<label for="password">Password:</label>
		<input type="password" id="password" name="password" required><br><br>
		<input type="submit" name="submit" value="Login">
	</form>
</body>
</html>

