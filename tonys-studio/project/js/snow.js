function snow() {
    var flake = document.createElement('div');
    // 雪花字符 ❄❉❅❆✻✼❇❈❊✥✺
    flake.innerHTML = '❅';
    flake.style.cssText = 'position:absolute;color:#fff;';

    //获取页面的高度 相当于雪花下落结束时Y轴的位置
    var documentHieght = window.innerHeight;
    //获取页面的宽度，利用这个数来算出，雪花开始时left的值
    var documentWidth = window.innerWidth;

    //定义生成一片雪花的毫秒数
    var millisec =10;
    setInterval(function() {
        var startLeft = Math.random() * documentWidth;
        var endLeft = Math.random() * documentWidth;
        var flakeSize = 3 + 20 * Math.random();
        var durationTime = 4000 + 7000 * Math.random();
        var startOpacity = 0.7 + 0.3 * Math.random();
        var endOpacity = 0.2 + 0.2 * Math.random();
        var cloneFlake = flake.cloneNode(true);

        cloneFlake.style.cssText += `
                left: ${startLeft}px;
                opacity: ${startOpacity};
                font-size:${flakeSize}px;
                top:-25px;
                    transition:${durationTime}ms;`;

        document.body.appendChild(cloneFlake);

        setTimeout(function() {
            cloneFlake.style.cssText += `
                        left: ${endLeft}px;
                        top:${documentHieght}px;
                        opacity:${endOpacity};`;

            setTimeout(function() {
                cloneFlake.remove();
            }, durationTime);
        }, 0);

    }, millisec);
}

snow();