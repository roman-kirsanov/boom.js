/**
 * @param {number} x
 * @param {number} y
 * @returns {Vec2}
 */
const vec2 = (x, y) => [ x, y ];

const view = new GraphicsView();
view.on('attach', () => console.log('view attached...'));
view.on('resize', () => console.log('view resized...'));
view.on('mousemove', ({ position }) => console.log(`view mousemove: ${position}`));
view.on('mouseenter', ({ position }) => console.log(`view mouseenter: ${position}`));
view.on('mouseexit', ({ position }) => console.log(`view mouseexit: ${position}`));
view.on('render', ({ context: gl }) => {
    console.log('view render...');
});

const window = new Window();
window.title = "Window 101";
window.size = vec2(640, 480);
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