/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the MIT license found in the
 *  LICENSE file in the root directory of this source tree.
 *
 */

use type Facebook\XHP\SVG\{svg, g, circle, animate};
use function Facebook\FBExpect\expect;

final class SvgTest extends Facebook\HackTest\HackTest {
  /**
   * Source: https://github.com/rendro/SVG-Spinner/blob/379a1169c4c24a35e1d000d061378c39eea997e6/images/fading-loader.svg
   *
   * License: Do What The F*ck You Want To Public License
   *
   * Edits made:
   *  - Removed the SVG version, since this is invalid SVG2
   *  - Removed the deprecated `attributeType` attribute.
   * Source: https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/attributeType
   */
  public async function testSvgImageFromTheInternetAsync(): Awaitable<void> {
    $svg =
      <svg
        xmlns="http://www.w3.org/2000/svg"
        width="110px"
        height="110px">
        <g transform="translate(5 5)">
          <circle cx="50" cy="0" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0s"
            />
          </circle>
          <circle cx="75" cy="6.6987298" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.1s"
            />
          </circle>
          <circle cx="93.3012702" cy="25" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.2s"
            />
          </circle>
          <circle cx="100" cy="50" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.3s"
            />
          </circle>
          <circle cx="93.3012702" cy="75" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.4s"
            />
          </circle>
          <circle cx="75" cy="93.3012702" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.5s"
            />
          </circle>
          <circle cx="50" cy="100" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.6s"
            />
          </circle>
          <circle cx="25" cy="93.3012702" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.7s"
            />
          </circle>
          <circle cx="6.6987298" cy="75" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.8s"
            />
          </circle>
          <circle cx="0" cy="50" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="0.9s"
            />
          </circle>
          <circle cx="6.6987298" cy="25" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="1s"
            />
          </circle>
          <circle cx="25" cy="6.6987298" r="5" style="opacity:0.3">
            <animate
              attributeName="opacity"
              from="1"
              to="0.3"
              dur="1.2s"
              repeatCount="indefinite"
              begin="1.1s"
            />
          </circle>
        </g>
      </svg>;
    expect(await $svg->toStringAsync())->toNotBeEmpty();
  }
}
