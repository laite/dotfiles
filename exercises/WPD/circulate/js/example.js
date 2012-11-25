$(window).load(function() {
    $("#monster").css("left", $("#monster").position().left).circulate({
            sizeAdjustment: 160,
            speed: 2000,
            width: -820,
            height: 500,
            loop: true,
            zIndexValues: [1, 50, 50, 1]
    });

});
