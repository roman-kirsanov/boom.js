



const window = new Window();
window.title = "Window 101";
window.size = [640, 480];
window.visible = true;
window.center();

window.on('close', () => application.exit());
