declare type Console = {
    readonly log: (...args: any[]) => void;
}

declare const console: Console;