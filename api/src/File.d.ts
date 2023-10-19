declare type FileMode = {
    read?: boolean;
    write?: boolean;
}

declare class File {
    public constructor(path: string, mode?: FileMode);
    public text(): Promise<string>;
    public json(): Promise<any>;
    public bytes(): Promise<Uint8Array>;
    public static Info(path: string): boolean;
    public static Exists(path: string): boolean;
    public static IsFile(path: string): boolean;
    public static IsDirectory(path: string): boolean;
    public static IsSymlink(path: string): boolean;
}