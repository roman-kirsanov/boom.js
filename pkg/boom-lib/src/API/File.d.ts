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