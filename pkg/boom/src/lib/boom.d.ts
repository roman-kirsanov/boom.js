declare type Application = {
    title: string;
    readonly on: (event: 'exit' | 'poll', callback: Function) => void;
    readonly off: (event: 'exit' | 'poll', callback: Function) => void;
    readonly exit: () => void;
}

declare const application: Application;

declare type Console = {
    readonly log: (...args: any[]) => void;
}

declare const console: Console;

declare type FileMode = {
    read?: boolean;
    write?: boolean;
}

declare type FileSeek = 'start' | 'current' | 'end';

declare class File {
    public constructor(path: string, mode?: FileMode);
    public text(): Promise<string>;
    public json(): Promise<any>;
    public bytes(): Promise<Uint8Array>;
    public position(): number;
    public read(buffer: Uint8Array): Promise<number>;
    public write(buffer: Uint8Array): Promise<void>;
    public seek(offset: number, mode: FileSeek): void;
    public close(): void;
    public static Info(path: string): object;
    public static Exists(path: string): boolean;
    public static IsFile(path: string): boolean;
    public static IsDirectory(path: string): boolean;
    public static IsSymlink(path: string): boolean;
}

declare type ImageFilter = 'nearest' | 'linear';

declare type ImagePosition = 'start' | 'center' | 'end' | 'stretch';

declare class Image {}

declare type Key = (
    'unknown' |
    '0' |
    '1' |
    '2' |
    '3' |
    '4' |
    '5' |
    '6' |
    '7' |
    '8' |
    '9' |
    'a' |
    'b' |
    'c' |
    'd' |
    'e' |
    'f' |
    'g' |
    'h' |
    'i' |
    'j' |
    'k' |
    'l' |
    'm' |
    'n' |
    'o' |
    'p' |
    'q' |
    'r' |
    's' |
    't' |
    'u' |
    'v' |
    'w' |
    'x' |
    'y' |
    'z' |
    'f1' |
    'f2' |
    'f3' |
    'f4' |
    'f5' |
    'f6' |
    'f7' |
    'f8' |
    'f9' |
    'f10' |
    'f11' |
    'f12' |
    'f13' |
    'f14' |
    'f15' |
    'f16' |
    'f17' |
    'f18' |
    'f19' |
    'f20' |
    'alt' |
    'arrowdown' |
    'arrowleft' |
    'arrowright' |
    'arrowup' |
    'backslash' |
    'capslock' |
    'comma' |
    'control' |
    'delete' |
    'end' |
    'equal' |
    'escape' |
    'forwarddelete' |
    'function' |
    'grave' |
    'help' |
    'home' |
    'leftbracket' |
    'meta' |
    'minus' |
    'mute' |
    'pagedown' |
    'pageup' |
    'period' |
    'quote' |
    'return' |
    'rightalt' |
    'rightbracket' |
    'rightcontrol' |
    'rightshift' |
    'semicolon' |
    'shift' |
    'slash' |
    'space' |
    'tab' |
    'volumedown' |
    'volumeup' |
    'keypad_clear' |
    'keypad_decimal' |
    'keypad_divide' |
    'keypad_enter' |
    'keypad_equal' |
    'keypad_minus' |
    'keypad_multiply' |
    'keypad_plus' |
    'keypad_0' |
    'keypad_1' |
    'keypad_2' |
    'keypad_3' |
    'keypad_4' |
    'keypad_5' |
    'keypad_6' |
    'keypad_7' |
    'keypad_8' |
    'keypad_9'
)

declare type KeyModifiers = {
    shift: boolean;
    control: boolean;
    meta: boolean;
    alt: boolean;
}


declare type Vec2 = [ number, number ];

declare type Vec4 = [ number, number, number, number ];

declare type NodePosition = 'relative' | 'absolute';

declare type NodeDirection = 'column' | 'row';

declare type NodeAlignment = 'start' | 'center' | 'end' | 'stretch';

declare type NodeJustify = 'start' | 'center' | 'end' | 'space-netween' | 'space-around' | 'space-evenly';

declare class Node {
    public readonly children: Node[];
    public readonly parent: Node | null;
    public readonly view: View | null;
    public readonly path: Node[];
    public readonly container: number[];
    public readonly transform: number[];
    public readonly active: boolean;
    public readonly hover: boolean;
    public readonly focused: boolean;
    public readonly focusedWithin: boolean;
    public readonly rect: Vec2;
    public tag: string | null;
    public text: string | null;
    public scale: Vec2;
    public anchor: Vec2;
    public position: Vec2;
    public scroll: Vec2;
    public size: Vec2;
    public clip: boolean;
    public rotate: number;
    public strokeWidth: number;
    public strokeRadius: number;
    public strokeColor: Vec4 | string;
    public fillColor: Vec4 | string;
    public image: Image | null;
    public imageSlice: Vec4 | null;
    public imageNPatch: Vec4 | null;
    public imageFilterMin: ImageFilter;
    public imageFilterMag: ImageFilter;
    public imagePositionX: ImagePosition;
    public imagePositionY: ImagePosition;
    public imageRepeatX: boolean;
    public imageRepeatY: boolean;
    public imageFlipX: boolean;
    public imageFlipY: boolean;
    public removeFromParent(): void;
    public addChild(child: Node): void;
    public removeChild(child: Node): void;
    public insertChild(child: Node, index: number): void;
    public replaceChild(oldChild: Node, newChild: Node): void;
    public on(event: 'attach', listener: () => void): void;
    public on(event: 'detach', listener: () => void): void;
    public on(event: 'resize', listener: () => void): void;
    public on(event: 'update', listener: () => void): void;
    public on(event: 'render', listener: () => void): void;
    public on(event: 'attach', listener: () => void): void;
    public on(event: 'focus', listener: () => void): void;
    public on(event: 'blur', listener: () => void): void;
    public on(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseenter', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseexit', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public on(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public off(event: 'attach', listener: () => void): void;
    public off(event: 'detach', listener: () => void): void;
    public off(event: 'resize', listener: () => void): void;
    public off(event: 'update', listener: () => void): void;
    public off(event: 'render', listener: () => void): void;
    public off(event: 'attach', listener: () => void): void;
    public off(event: 'focus', listener: () => void): void;
    public off(event: 'blur', listener: () => void): void;
    public off(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseenter', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseexit', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public off(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
}

declare type Process = {
    readonly argv: Readonly<string[]>;
    readonly env: Readonly<Record<string, string>>;
    readonly workDir: string;
    readonly execDir: string;
    readonly execPath: string;
    readonly exit: (code?: number) => void;
    readonly stdout: {
        readonly write: (...args: (string | Uint8Array)[]) => void;
    },
    readonly stderr: {
        readonly write: (...args: (string | Uint8Array)[]) => void;
    }
}

declare const process: Process;

declare class Timeout {}

declare const setTimeout: (fn: Function, timeout: number) => Timeout;

declare const setInterval: (fn: Function, interval: number) => Timeout;

declare const clearTimeout: (handle: Timeout) => void;

declare type DeepReadonly<T> = {
    readonly [K in keyof T]: DeepReadonly<T[K]>;
}

declare class View {
    public readonly children: View[];
    public readonly parent: View | null;
    public position: Vec2;
    public size: Vec2;
    public removeFromParent(): void;
    public addChild(child: View): void;
    public removeChild(child: View): void;
    public replaceChild(child1: View, child2: View): void;
    public insertChild(child: View, index: number): void;
    public on(event: 'attach', listener: () => void): void;
    public on(event: 'detach', listener: () => void): void;
    public on(event: 'resize', listener: () => void): void;
    public on(event: 'focus', listener: () => void): void;
    public on(event: 'blur', listener: () => void): void;
    public on(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseenter', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseexit', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public on(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public off(event: 'attach', listener: () => void): void;
    public off(event: 'detach', listener: () => void): void;
    public off(event: 'resize', listener: () => void): void;
    public off(event: 'focus', listener: () => void): void;
    public off(event: 'blur', listener: () => void): void;
    public off(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseenter', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseexit', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public off(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
}

declare class GraphicsView extends View {
    public on(event: 'attach', listener: () => void): void;
    public on(event: 'detach', listener: () => void): void;
    public on(event: 'resize', listener: () => void): void;
    public on(event: 'focus', listener: () => void): void;
    public on(event: 'blur', listener: () => void): void;
    public on(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseenter', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseexit', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public on(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public on(event: 'render', listener: () => void): void;
    public off(event: 'attach', listener: () => void): void;
    public off(event: 'detach', listener: () => void): void;
    public off(event: 'resize', listener: () => void): void;
    public off(event: 'focus', listener: () => void): void;
    public off(event: 'blur', listener: () => void): void;
    public off(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseenter', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseexit', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'mbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public off(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public off(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public off(event: 'render', listener: () => void): void;
}

declare class Window {
    public titlebar: boolean;
    public visible: boolean;
    public sizable: boolean;
    public closable: boolean;
    public maximizable: boolean;
    public minimizable: boolean;
    public maximized: boolean;
    public minimized: boolean;
    public topmost: boolean;
    public pixelratio: number;
    public size: Vec2;
    public title: string;
    public view: View;
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
    public off(event: 'show', listener: () => void): void;
    public off(event: 'hide', listener: () => void): void;
    public off(event: 'close', listener: () => void): void;
    public off(event: 'resize', listener: () => void): void;
    public off(event: 'maximize', listener: () => void): void;
    public off(event: 'minimize', listener: () => void): void;
    public off(event: 'demaximize', listener: () => void): void;
    public off(event: 'deminimize', listener: () => void): void;
    public off(event: 'pixelratio', listener: () => void): void;
}