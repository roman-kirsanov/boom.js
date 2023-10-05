const app = new App();
app.on('exit', () => app.exit());

const win = new Window();
win.on('close', () => app.exit());

win.title = "CLI Window";
win.size = [640, 480];
win.closable = true;
win.sizable = true;
win.visible = true;
win.center();

win.on('mousemove', ({ position, modifiers }) => {
    process.stdout.write(`position: ${position}\n`);
});