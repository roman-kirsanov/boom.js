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