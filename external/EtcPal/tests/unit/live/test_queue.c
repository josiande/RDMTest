/******************************************************************************
 * Copyright 2020 ETC Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************
 * This file is a part of EtcPal. For more information, go to:
 * https://github.com/ETCLabs/EtcPal
 ******************************************************************************/

#include "etcpal/queue.h"

#include "unity_fixture.h"

TEST_GROUP(etcpal_queue);

TEST_SETUP(etcpal_queue)
{
}

TEST_TEAR_DOWN(etcpal_queue)
{
}

TEST(etcpal_queue, can_send_and_receive)
{
  etcpal_queue_t queue;

  // Create queue for 10 chars
  TEST_ASSERT_TRUE(etcpal_queue_create(&queue, 10, sizeof(char)));
  char data = 0xDE;
  TEST_ASSERT_TRUE(etcpal_queue_send(&queue, &data));
  char receivedData;
  TEST_ASSERT_TRUE(etcpal_queue_receive(&queue, &receivedData));
  TEST_ASSERT_EQUAL(data, receivedData);
  etcpal_queue_destroy(&queue);
}

TEST(etcpal_queue, will_timeout_on_send)
{
  etcpal_queue_t queue;

  // Create queue for 3 chars
  TEST_ASSERT_TRUE(etcpal_queue_create(&queue, 3, sizeof(char)));
  char data = 0xDE;
  TEST_ASSERT_TRUE(etcpal_queue_timed_send(&queue, &data, 0));
  data = 0xAD;
  TEST_ASSERT_TRUE(etcpal_queue_timed_send(&queue, &data, 0));
  data = 0xBE;
  TEST_ASSERT_TRUE(etcpal_queue_timed_send(&queue, &data, 0));

  // This one should NOT work because we are over our size
  data = 0xEF;
  TEST_ASSERT_FALSE(etcpal_queue_timed_send(&queue, &data, 10));

  etcpal_queue_destroy(&queue);
}

TEST(etcpal_queue, will_timeout_on_receive)
{
  etcpal_queue_t queue;

  // Create queue for 3 chars
  TEST_ASSERT_TRUE(etcpal_queue_create(&queue, 3, sizeof(char)));
  char data = 0xDE;
  TEST_ASSERT_TRUE(etcpal_queue_timed_send(&queue, &data, 0));
  char receivedData = 0x00;
  TEST_ASSERT_TRUE(etcpal_queue_timed_receive(&queue, &receivedData, 10));
  TEST_ASSERT_FALSE(etcpal_queue_timed_receive(&queue, &receivedData, 10));

  etcpal_queue_destroy(&queue);
}

TEST(etcpal_queue, can_detect_empty)
{
  etcpal_queue_t queue;

  // Create queue for 3 chars
  TEST_ASSERT_TRUE(etcpal_queue_create(&queue, 4, sizeof(char)));
  TEST_ASSERT_TRUE(etcpal_queue_is_empty(&queue));

  char data = 0xDE;
  TEST_ASSERT_TRUE(etcpal_queue_timed_send(&queue, &data, 0));
  TEST_ASSERT_FALSE(etcpal_queue_is_empty(&queue));

  data = 0xAD;
  TEST_ASSERT_TRUE(etcpal_queue_timed_receive(&queue, &data, 0));
  TEST_ASSERT_TRUE(etcpal_queue_is_empty(&queue));

  TEST_ASSERT_TRUE(etcpal_queue_timed_send(&queue, &data, 0));
  TEST_ASSERT_FALSE(etcpal_queue_is_empty(&queue));

  etcpal_queue_destroy(&queue);
}

TEST_GROUP_RUNNER(etcpal_queue)
{
  RUN_TEST_CASE(etcpal_queue, can_send_and_receive);
  RUN_TEST_CASE(etcpal_queue, will_timeout_on_send);
  RUN_TEST_CASE(etcpal_queue, will_timeout_on_receive);
  RUN_TEST_CASE(etcpal_queue, can_detect_empty);
}
