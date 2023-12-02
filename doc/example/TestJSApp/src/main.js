

const view = new View();
view.on('attach', () => console.log('view attached...'));
view.on('resize', () => console.log('view resized...'));
view.on('mousemove', ({ position }) => {
    console.log(`view mousemove: ${position}`);
})

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