<!-- creating login form  -->
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"/>
        <title>Login</title>
        <link rel="stylesheet" href="style.css"/>
    </head>
    <body>
        <?php
            require('db.php');
            session_start();
            // when form is submitted, check and create student session
            if(isset($_POST['stdID']))
            {
                $stdID = stripslashes($_REQUEST['stdID']);
                $stdID = mysqli_real_escape_string($con, $stdID);
                
                $passwd = stripslashes($_REQUEST['passwd']);
                $passwd = mysqli_real_escape_string($con, $passwd);

                $query = "select * from std where stdID='$stdID' and passwd='$passwd'";

                $result = mysqli_query($con, $query);
                $rows = mysqli_num_rows($result);

                if($rows==1)
                {
                    $_SESSION['stdID'] = $stdID;
                    // Redirect to user dashboard page
                    header("location: dashboard.php");
                }
                else
                {
                    echo "<div class='form'>
                    <h3>Incorrect Student ID</h3>
                    <br/>
                    <p class='link'>Click here to <a href='login.php'>Login</a> again.</p>
                    </div>";
                }
            }
            else
            {

        ?>
        <form class="form" method="post" name="login">
                <h1 class="login-title">Login</h1>
                <input type="text" class="login-input" name="stdID" placeholder="Student ID" autofocus="true" required/>
                <input type="password" class="login-input" name="passwd" placeholder="Password" required/>

                <input type="submit" value="Login" name="submit" class="login-button"/>
                <p class="link"><a href="registration.php">New Registration</a></p>
        </form>
        <?php
            }
        ?>
    </body>
</html>