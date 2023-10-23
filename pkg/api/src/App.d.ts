declare class App {
    public get title(): string;
    public set title(title: string);
    public on(event: 'exit' | 'poll', callback: Function): void;
    public off(event: 'exit' | 'poll', callback: Function): void;
    public exit(): void;
}