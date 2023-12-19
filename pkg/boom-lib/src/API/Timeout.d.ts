declare class Timeout {}

declare const setTimeout: (fn: Function, timeout: number) => Timeout;

declare const setInterval: (fn: Function, interval: number) => Timeout;

declare const clearTimeout: (handle: Timeout) => void;