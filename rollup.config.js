import typescriptPlugin from 'rollup-plugin-typescript2';

import { tmpdir } from 'os';
import { join as pathJoin } from 'path';

import pkg from './package.json';

const cacheRoot = pathJoin(tmpdir(), '.rpt2_cache');

const src = pathJoin(__dirname, 'src');
const dist = pathJoin(__dirname, 'dist');

// eslint-disable-next-line import/no-default-export
export default {
	input: pathJoin(src, 'index.ts'),
	plugins: [
		typescriptPlugin({
			cacheRoot,

			useTsconfigDeclarationDir: false,

			tsconfigOverride: {
				outDir: dist,
				rootDir: src,
				include: [src]
			}
		})
	],
	external: [
		'util'
	],
	output: [
		{
			file: `${pkg.main}.js`,
			format: 'cjs',
			exports: 'named'
		},
		{
			file: `${pkg.main}.mjs`,
			format: 'esm'
		}
	]
};