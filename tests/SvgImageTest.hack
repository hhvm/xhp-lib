/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use namespace Facebook\XHP\Core as x;
use type Facebook\XHP\HTML\{svg, g, circle, animate};

use function Facebook\FBExpect\expect;


final class SvgImageTest extends Facebook\HackTest\HackTest {
  /**
   * Source: https://github.com/rendro/SVG-Spinner/blob/379a1169c4c24a35e1d000d061378c39eea997e6/images/spinning-loader.svg
   * License: Do What The F*ck You Want To Public License
   * https://choosealicense.com/licenses/wtfpl/
   *
   * This is the most permissive SVG image I could find.
   * This license imposes zero limitations.
   * We can therefore freely relicense it under the xhp-lib MIT license.
   */
  public async function testSvgRendering(): Awaitable<void> {
    $svg =
      <svg
        xmlns="http://www.w3.org/2000/svg"
        version="1.1"
        width="110px"
        height="110px">
        <g>
          <circle cx="50" cy="0" r="5" transform="translate(5 5)" />
          <circle cx="75" cy="6.6987298" r="5" transform="translate(5 5)" />
          <circle cx="93.3012702" cy="25" r="5" transform="translate(5 5)" />
          <circle cx="100" cy="50" r="5" transform="translate(5 5)" />
          <circle cx="93.3012702" cy="75" r="5" transform="translate(5 5)" />
          <circle cx="75" cy="93.3012702" r="5" transform="translate(5 5)" />
          <circle cx="50" cy="100" r="5" transform="translate(5 5)" />
          <circle cx="25" cy="93.3012702" r="5" transform="translate(5 5)" />
          <circle cx="6.6987298" cy="75" r="5" transform="translate(5 5)" />
          <circle cx="0" cy="50" r="5" transform="translate(5 5)" />
          <circle cx="6.6987298" cy="25" r="5" transform="translate(5 5)" />
          <circle cx="25" cy="6.6987298" r="5" transform="translate(5 5)" />
        </g>
      </svg>;
    expect(await $svg->toStringAsync())->toNotBeEmpty();
  }
}
