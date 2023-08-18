<!-- logout or destroy the session -->
<?php
    session_start();
    // destroy session
    if(session_destroy())
    {
        // redirecting to login page
        header("location: login.php");
    }
?>