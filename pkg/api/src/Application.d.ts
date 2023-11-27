declare type Application = {
    title: string;
    readonly on(event: 'exit' | 'poll', callback: Function): void;
    readonly off(event: 'exit' | 'poll', callback: Function): void;
    readonly exit(): void;
}

declare const application: Application;