// Initialize Phaser, and creates a 400x490px game
var game = new Phaser.Game(400, 490, Phaser.AUTO, 'game_div');
var game_state = {};
var space_direction_right = true;
var space_text;

// Creates a new 'main' state that will contain the game
game_state.main = function() { };  
game_state.main.prototype = {

    // Function called first to load all the assets
    preload: function() { 
        // Change the background color of the game
        this.game.stage.backgroundColor = '#71c5cf';

        // Load the bird sprite
        this.game.load.image('bird', 'assets/helixthegod.png');  

        // Load the pipe sprite
        this.game.load.image('pipe', 'assets/pokepc.png');      
    },

    // Fuction called after 'preload' to setup the game 
    create: function() { 
        // Display the bird on the screen
        this.bird = this.game.add.sprite(100, 245, 'bird');
        
        // Add gravity to the bird to make it fall
        this.bird.body.gravity.y = 1000; 

        // Call the 'jump' function when the spacekey is hit
        space_key = this.game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
        space_key.onDown.add(this.jump, this); 

        // Create a group of 20 pipes
        this.pipes = game.add.group();
        this.pipes.createMultiple(20, 'pipe');  

        // Timer that calls 'add_row_of_pipes' ever 1.5 seconds
        this.timer = this.game.time.events.loop(1500, this.add_row_of_pipes, this);           

        // Add a score label on the top left of the screen
        this.score = 0;
        var style = { font: "30px Arial", fill: "#ffffff" };
        this.label_score = this.game.add.text(20, 20, "0", style);  
    },

    // This function is called 60 times per second
    update: function() {
        // If the bird is out of the world (too high or too low), call the 'restart_game' function
        if (this.bird.inWorld == false) {
            this.restart_game();
        }

        // If the bird overlap any pipes, call 'restart_game'
        this.game.physics.overlap(this.bird, this.pipes, this.restart_game, null, this);  
    },

    // Make the bird jump 
    jump: function() {
        // Add a vertical velocity to the bird
        this.bird.body.velocity.y = -350;
    },

    // Restart the game
    restart_game: function() {
        // Remove the timer
        this.game.time.events.remove(this.timer);
        // TODO Display the score of user once game is over on the screen
        console.log("Your final score is: " + this.score);
        console.log("Remember to change this code one I get better at Javascript");
        /* 
         * An easter egg, easter egg! :D
         *       .-"-.
         *     .'=^=^='.
         *    /=^=^=^=^=\
         *   :=^=^=^=^=^=;
         *   |^=^=^=^=^=^|
         *   :=^=^=^=^=^=:
         *    \=^=^=^=^=/
         *     `.=^=^=.'
         *       `~~~`
         * */
        // console.log("flag{easter_eggs_are_fun_314159265}");
        this.game.state.start('main_menu');
    },

    // Add a pipe on the screen
    add_one_pipe: function(x, y) {
        // Get the first dead pipe of our group
        var pipe = this.pipes.getFirstDead();

        // Set the new position of the pipe
        pipe.reset(x, y);

         // Add velocity to the pipe to make it move left
        pipe.body.velocity.x = -200; 
               
        // Kill the pipe when it's no longer visible 
        pipe.outOfBoundsKill = true;
    },

    // Add a row of 6 pipes with a hole somewhere in the middle
    add_row_of_pipes: function() {
        var hole = Math.floor(Math.random()*5)+1;
        
        for (var i = 0; i < 8; i++)
            if (i != hole && i != hole +1) 
                this.add_one_pipe(400, i*60+10);   
    
        this.score += 1;
        this.label_score.content = this.score;  
    }
};

game_state.main_menu = function() { };
game_state.main_menu.prototype = {
	preload: function() {
        this.game.stage.backgroundColor = '#71c5cf';
        this.game.load.image('title', 'assets/title_image.png');
        this.game.load.image('space', 'assets/press_space.png');
	},
    create: function() {
        // var font_style = { font: 'bold 32pt "Press Start 2P"', fill: "#00A1E7", align: "center" };
        // this.titletext = this.game.add.text(this.game.world.centerX - 127, this.game.world.centerY - 80, "Save Helix!", font_style);
        this.titleimage = this.add.sprite(this.game.world.centerX - 127, this.game.world.centerY - 80, 'title');
        this.spaceimage = this.add.sprite(this.game.world.centerX, this.game.world.centerY + 30, 'space');
        this.spaceimage.anchor.setTo(0.5, 0.5);
        title_space_key = this.game.input.keyboard.addKey(Phaser.Keyboard.SPACEBAR);
        title_space_key.onDown.add(this.start_game, this); 
    },
    update: function() {
        if (this.game.input.keyboard.isDown(Phaser.Keyboard.SPACE_BAR)) {
            console.log(true);
        }
        if (space_direction_right) { 
            if (this.spaceimage.angle <= 20) {
                this.spaceimage.angle += 1;
            } else {
                space_direction_right = false;
                this.spaceimage.angle -= 1;
            }
        } else {
            if (this.spaceimage.angle >= -20) {
                this.spaceimage.angle -= 1;
            } else {
                space_direction_right = true;
                this.spaceimage.angle += 1;
            }
        }
    },
    start_game: function() {
        this.game.state.start('main')
    }
}


// Add and start the 'main' state to start the game
game.state.add('main_menu', game_state.main_menu);  
game.state.add('main', game_state.main);  
game.state.start('main_menu'); 
