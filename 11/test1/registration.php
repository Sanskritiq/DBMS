<!-- creating registration form -->
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8"/>
        <title>Registration</title>
        <link rel="stylesheet" href="style.css"/>
    </head>
    <body>
        <?php
            require('db.php');
            // when form is submitted, insert values into the db
            if(isset($_REQUEST['stdID']))
            {
                // remove backslashes
                $stdID = stripslashes($_REQUEST['stdID']);
                // escapes special chars in a string
                $stdID = mysqli_real_escape_string($con, $stdID);
                
                $email = stripslashes($_REQUEST['email']);
                $email = mysqli_real_escape_string($con, $email);
                
                $passwd = stripslashes($_REQUEST['passwd']);
                $passwd = mysqli_real_escape_string($con, $passwd);

                $stdName = stripslashes($_REQUEST['stdName']);
                $stdName = mysqli_real_escape_string($con, $stdName);

                $DoJ = stripslashes($_REQUEST['DoJ']);
                $DoJ = mysqli_real_escape_string($con, $DoJ);

                $Age = stripslashes($_REQUEST['Age']);
                $Age = (int)mysqli_real_escape_string($con, $Age);

                $department = stripslashes($_REQUEST['department']);
                $department = mysqli_real_escape_string($con, $department);

                $mobileNo = stripslashes($_REQUEST['mobileNo']);
                $mobileNo = (int)mysqli_real_escape_string($con, $mobileNo);

                $query = "insert into std (stdID, passwd, stdName, DoJ, Age, department, mobileNo, email) values ('$stdID', '$passwd', '$stdName', '$DoJ', $Age, '$department', $mobileNo, '$email')";

                $result = mysqli_query($con, $query);

                if($result)
                {
                    echo "<div class='form'>
                    <h3>You are registered successfully</h3>
                    <br/>
                    <p class='link'>
                    Click here to <a href='login.php'>Login</a>
                    </p>
                    </div>";
                }
                else
                {
                    echo "<div class='form'>
                    <h3>Required fields are missing</h3>
                    <br/>
                    <p class='link'>
                    Click here to <a href='registration.php'>Register</a> again.
                    </p>
                    </div>";
                }
            }
            else
            {

        ?>
        
        <form class="form" action="", method="post">

            <h1 class="login-title">Registration</h1>
            <input type="text" class="login-input" name="stdID" placeholder="Student ID" required/>
            <input type="text" class="login-input" name="email" placeholder="Email Address" required/>
            <input type="password" class="login-input" name="passwd" placeholder="Password" required/>

            <h1 class="login-title">Other Credentials</h1>
            <input type="text" class="login-input" name="stdName" placeholder="Student Name">
            <input type="date" class="login-input" name="DoJ" placeholder="Date of Joining">
            <input type="number" class="login-input" name="age" placeholder="Age">
            <input type="text" class="login-input" name="department" placeholder="Department">
            <input type="number" class="login-input" name="mobileNo" placeholder="Mobile Number (6 digits)">
            
            <input type="submit" name="submit" value="Register" class="login-button">
            <p class="link"><a href="login.php">Click to login</a></p>
        </form>

        <?php
            }
        ?>
    </body>
</html>