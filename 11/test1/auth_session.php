<!-- session create for logged in students -->
<?php
    session_start();
    if(!isset($_SESSION["stdID"]))
    {
        header("location: login.php");
        exit();
    }
?>