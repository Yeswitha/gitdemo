 // when the document is fully loaded add event handlers to appropriate elements
 $(document).ready(function () {
    //1. attach game.setTheme function to change event on select element with id 'category'
    
    //2. attach game.begin function to click event on button element with id 'start-btn'
    
    //3. attach game.reset function to click event on button element with id 'reset-btn'
    
    //4. attach game.updateLevel function to click event on i element in li in an element with class 'level'  
    $('#category').change(game.setTheme);
    $('#start-btn').click(game.begin);
    $('#reset-btn').click(game.reset);
    $('.level').find('i').click(game.updateLevel);
  });