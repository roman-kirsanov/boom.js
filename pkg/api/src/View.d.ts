declare class View {
    public children: View[];
    public parent: View;
    public position: Vec2;
    public size: Vec2;
    public removeFromParent(): void;
    public addChild(child: View): void;
    public removeChild(child: View): void;
    public replaceChild(child1: View, child2: View): void;
    public insertChild(child: View, index: number): void;
    public on(event: 'mousemove', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mousewheel', listener: (info: DeepReadonly<{ wheel: Vec2, modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'mouseclick', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttondown', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'lbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'rbuttonup', listener: (info: DeepReadonly<{ position: Vec2; modifiers: KeyModifiers; }>) => void): void;
    public on(event: 'keydown', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
    public on(event: 'keyup', listener: (info: DeepReadonly<{ key: Key; modifiers: KeyModifiers; input: string; }>) => void): void;
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