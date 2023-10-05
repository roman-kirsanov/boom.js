import chalk from 'chalk'

export const abort = (message: string) => {
    process.stderr.write(`${chalk.bgRed(' ERROR ')} ${message}\n`);
}