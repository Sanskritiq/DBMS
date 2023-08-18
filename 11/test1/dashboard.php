<!-- making students' dashboard -->
<?php
    // authorising the student user
    include("auth_session.php");
?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>Dashboard</title>
        <link rel="stylesheet" href="style.css"/>
    </head>
    <body>
        <div class="form">
            <p>Welcome <?php echo $_SESSION['stdID']; ?>.</p>
            <p>This is the Dashboard.</p>
            <p><a href="logout.php">Logout</a></p>
        </div>
    </body>
</html>