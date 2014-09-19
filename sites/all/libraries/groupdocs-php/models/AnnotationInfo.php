<?php
/**
 *  Copyright 2012 GroupDocs.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

/**
 * 
 *
 * NOTE: This class is auto generated by the swagger code generator program. Do not edit the class manually.
 *
 */
class AnnotationInfo {

  static $swaggerTypes = array(
      'guid' => 'string',
      'documentGuid' => 'string',
      'sessionGuid' => 'string',
      'creatorGuid' => 'string',
      'box' => 'Rectangle',
      'pageNumber' => 'int',
      'annotationPosition' => 'Point',
      'range' => 'Range',
      'svgPath' => 'string',
      'type' => 'string',
      'access' => 'string',
      'replies' => 'array[AnnotationReplyInfo]',
      'createdOn' => 'string',
      'fontColor' => 'int',
      'fieldText' => 'string',
      'fontFamily' => 'string',
      'fontSize' => 'float'

    );

  public $guid; // string
  public $documentGuid; // string
  public $sessionGuid; // string
  public $creatorGuid; // string
  public $box; // Rectangle
  public $pageNumber; // int
  public $annotationPosition; // Point
  public $range; // Range
  public $svgPath; // string
  public $type; // string
  public $access; // string
  public $replies; // array[AnnotationReplyInfo]
  public $createdOn; // string
  public $fontColor; // int
  public $fieldText; // string
  public $fontFamily; // string
  public $fontSize; // float
  }
