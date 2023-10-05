declare class Window {
    public get titlebar(): boolean;
    public get visible(): boolean;
    public get sizable(): boolean;
    public get closable(): boolean;
    public get maximizable(): boolean;
    public get minimizable(): boolean;
    public get maximized(): boolean;
    public get minimized(): boolean;
    public get topmost(): boolean;
    public get pixelratio(): number;
    public get size(): Vec2;
    public get title(): string;
    public set titlebar(titlebar: boolean);
    public set visible(visible: boolean);
    public set sizable(sizable: boolean);
    public set closable(closable: boolean);
    public set maximizable(maximizable: boolean);
    public set minimizable(minimizable: boolean);
    public set maximized(maximized: boolean);
    public set minimized(minimized: boolean);
    public set topmost(topmost: boolean);
    public set size(size: Vec2);
    public set title(title: string);
    public center(): void;
    public on(event: 'show', listener: () => void): void;
    public on(event: 'hide', listener: () => void): void;
    public on(event: 'close', listener: () => void): void;
    public on(event: 'resize', listener: () => void): void;
    public on(event: 'maximize', listener: () => void): void;
    public on(event: 'minimize', listener: () => void): void;
    public on(event: 'demaximize', listener: () => void): void;
    public on(event: 'deminimize', listener: () => void): void;
    public on(event: 'pixelratio', listener: () => void): void;
    public on(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public on(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public off(event: 'show', listener: () => void): void;
    public off(event: 'hide', listener: () => void): void;
    public off(event: 'close', listener: () => void): void;
    public off(event: 'resize', listener: () => void): void;
    public off(event: 'maximize', listener: () => void): void;
    public off(event: 'minimize', listener: () => void): void;
    public off(event: 'demaximize', listener: () => void): void;
    public off(event: 'deminimize', listener: () => void): void;
    public off(event: 'pixelratio', listener: () => void): void;
    public off(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public off(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
}