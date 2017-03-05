<?php
    require_once '../../php/Require.php';
    $loggedIn = login_check();
    // Get flag for the user logged in
    if ($loggedIn) {
        echo <<<HTML
<!DOCTYPE html>
<html>
    
<head>
  <meta charset="utf-8" />
  <title>Flappy Bird Clone</title>

  <style>
    #game_div, p, h4 {
      width: 400px;
      margin: auto;
      margin-top: 20px;
    }
  </style>
  <script type="text/javascript" src="phaser.min.js"></script>
  <script type="text/javascript" src="main.js"></script>
</head>

<body>

  <center>
    <h1>Save Helix!</h1>
    <h3>Game under development: build 1.1.9001</h3>
  </center>


  <div id="game_div"> </div>

  <p>Save the almighty powerful Helix from being placed into the Pokemon Center PC! We shall not lose our savior to the hands of the Australian Trolls!</p>
    <h4>Note: This is definetly not a complete rip off of "Flappy Bird" and all content found in this game is completely original. &#169;H4x-r-u$</h4>
</body>

</html>
HTML;
    } else {
        echo '<h1>You are not currently logged in. Please login before accessing this challenge.</h1>';
    }
?>
