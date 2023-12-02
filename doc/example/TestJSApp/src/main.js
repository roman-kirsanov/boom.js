

const view = new View();

const window = new Window();
window.title = "Window 101";
window.size = [640, 480];
window.visible = true;
window.view = view;
window.on('resize', () => {
    console.log(`window size: ${window.size}`);
});
window.on('close', () => {
    console.log('Exiting...');
    application.exit();
});
window.center();