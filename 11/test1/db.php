<!-- connect to the database -->
<?php

    $con = mysqli_connect("localhost:3306", "root", "password", "ASSIGN11_students");
    if (mysqli_connect_errno())
    {
      echo "Failed to connect to MySQL: " . mysqli_connect_errno();
    }
?>